package com.none.ConferenceMS;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.io.ByteArrayResource;
import org.springframework.core.io.Resource;
import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.StringUtils;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.util.List;

import javax.servlet.http.HttpSession;

import com.none.ConferenceMS.exception.FileStorageException;
import com.none.ConferenceMS.models.*;

@Controller
public class MainController {

    @Autowired
    CandidateRepository candidateRepo;
    @Autowired
    PaperRepository paperRepo;
    @Autowired
    ReviewerRepository reviewerRepo;

    @RequestMapping(value = "/", method = RequestMethod.GET)
    public String home(Model model) {
        model.addAttribute("candidate", new Candidate());
        return "index";
    }

    @RequestMapping(value = "/register", method = RequestMethod.POST)
    public String register(@ModelAttribute Candidate candidate, HttpSession session) {
        // save to db
        Candidate savedCandidate = candidateRepo.save(candidate);

        // set session
        session.setAttribute("firstName", candidate.getFirstName());
        session.setAttribute("userId", savedCandidate.getId());
        
        return "registration-status";
    }

    @RequestMapping(value = "/login", method = RequestMethod.POST)
    public String login(@ModelAttribute Candidate candidate, Model model, HttpSession session) {

        List<Candidate> c = candidateRepo.findByEmail(candidate.getEmail());
        Candidate toCheck;
        if (c.isEmpty()) {
            System.out.println(candidate.getEmail() + " is empty");
            return "redirect:/";
        } else {
            toCheck = c.get(0);

            if (!toCheck.getPassword().equals(candidate.getPassword())) {
                System.out.println(toCheck.getPassword() + " dont match with " + candidate.getPassword());
                return "redirect:/";
            }

            // login successful
            // set session
            session.setAttribute("userId", toCheck.getId());
            session.setAttribute("firstName", candidate.getFirstName());
        }
        
        return "redirect:/status";
    }

    @RequestMapping(value = "/status", method = RequestMethod.GET)
    public String status(@ModelAttribute Paper paper, Model model, HttpSession session) {
        if (session.getAttribute("userId") == null ) {
            return "redirect:/";
        }

        List<Paper> p = paperRepo.findBySubmittedBy((int)session.getAttribute("userId"));

        if (p.isEmpty()) {
            model.addAttribute("statusMessage", "not submitted");
        } else if (p.get(0).getStatus() == 0) {
            model.addAttribute("statusMessage", "pending");
        } else if (p.get(0).getStatus() == -1) {
            model.addAttribute("statusMessage", "rejected");
        } else if (p.get(0).getStatus() == 1) {
            model.addAttribute("statusMessage", "accepted");
        }

        return "status";
    }

    @RequestMapping(value = "/submit-paper", method = RequestMethod.POST)
    public String submitPaper(@RequestParam String title, @RequestParam MultipartFile file, HttpSession session) {
        byte[] fileData;
        
        try {
            fileData = file.getBytes();
        } catch (IOException e) {
            throw new FileStorageException("Error reading " + file.getName());
        }

        Paper paper = new Paper(title, fileData, StringUtils.cleanPath(file.getOriginalFilename()), file.getContentType());
        paper.setSubmittedBy((int)session.getAttribute("userId"));
        Paper savedPaper = paperRepo.save(paper);

        return "redirect:/status";
    }

    @RequestMapping(value = "/update-paper", method = RequestMethod.POST)
    public String updatePaper(@RequestParam MultipartFile file, HttpSession session) {
        byte[] fileData;
        
        try {
            fileData = file.getBytes();
        } catch (IOException e) {
            throw new FileStorageException("Error reading " + file.getName());
        }

        Paper paper = paperRepo.findBySubmittedBy((int)session.getAttribute("userId")).get(0);
        paper.setFileName(StringUtils.cleanPath(file.getOriginalFilename()));
        paper.setFileType(file.getContentType());
        paper.setFile(fileData);
        Paper savedPaper = paperRepo.save(paper);

        return "redirect:/status";
    }

    @RequestMapping(value = "/candidate-dashboard", method = RequestMethod.GET)
    public String candidateDashboard() {
        return "candidate-dashboard";
    }

    @RequestMapping(value = "/reviewer-login", method = RequestMethod.GET)
    public String reviewerLogin(@ModelAttribute Reviewer reviewer) {
        return "reviewer-login";
    }

    @RequestMapping(value = "/reviewer-login", method = RequestMethod.POST)
    public String reviewerLoginPost(@ModelAttribute Reviewer reviewer, HttpSession session) {
        List<Reviewer> r = reviewerRepo.findByEmail(reviewer.getEmail());
        Reviewer toCheck;
        
        if (r.isEmpty()) {
            System.out.println(reviewer.getEmail() + " is empty");
            return "redirect:/reviewer-login";
        } else {
            toCheck = r.get(0);

            if (!toCheck.getPassword().equals(reviewer.getPassword())) {
                System.out.println(toCheck.getPassword() + " dont match with " + reviewer.getPassword());
                return "redirect:/";
            }

            // login successful
            // set session
            session.setAttribute("userId", toCheck.getId());
            session.setAttribute("firstName", reviewer.getFirstName());
            session.setAttribute("reviewer", true);
        }

        return "redirect:/reviewer-dashboard";
    }

    @RequestMapping(value = "/reviewer-dashboard", method = RequestMethod.GET)
    public String reviewerDashboard(HttpSession session, Model model) {
        if (session.getAttribute("userId") == null) {
            return "redirect:/reviewer-login";
        }

        List<Paper> papers = paperRepo.findAll();
        List<Candidate> candidates = candidateRepo.findAll();

        model.addAttribute("papers", papers);
        model.addAttribute("candidates", candidates);
        return "reviewer-dashboard";
    }

    @RequestMapping(value = "/download/{fileId}", method = RequestMethod.GET)
    public ResponseEntity<Resource> downloadFile(@PathVariable int fileId) {
        // Load file from database
        Paper paper = paperRepo.getOne(fileId);

        return ResponseEntity.ok()
                .contentType(MediaType.parseMediaType(paper.getFileType()))
                .header(HttpHeaders.CONTENT_DISPOSITION, "attachment; filename=\"" + paper.getFileName() + "\"")
                .body(new ByteArrayResource(paper.getFile()));
    }

    @RequestMapping(value = "/set-status/{action}/{paperId}", method = RequestMethod.GET)
    public String setStatus(@PathVariable String action, @PathVariable int paperId, HttpSession session) {
        if (session.getAttribute("userId") == null) {
            return "redirect:/reviewer-login";
        }

        Paper paper = paperRepo.getOne(paperId);

        if (action.equals("accept")) {
            paper.setStatus(1);
        } else if (action.equals("reject")) {
            paper.setStatus(-1);
        }

        paper.setReviewedBy((int)session.getAttribute("userId"));

        paperRepo.save(paper);

        return "redirect:/reviewer-dashboard";
    }

    @RequestMapping(value = "/logout", method = RequestMethod.GET)
    public String logout(HttpSession session) {
        session.invalidate();

        return "redirect:/";
    }
}